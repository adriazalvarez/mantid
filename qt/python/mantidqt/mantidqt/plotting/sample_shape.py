# Mantid Repository : https://github.com/mantidproject/mantid
#
# Copyright &copy; 2022 ISIS Rutherford Appleton Laboratory UKRI,
#   NScD Oak Ridge National Laboratory, European Spallation Source,
#   Institut Laue - Langevin & CSNS, Institute of High Energy Physics, CAS
# SPDX - License - Identifier: GPL - 3.0 +
#  This file is part of the mantid workbench.
#
#
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection

from mantid.api import AnalysisDataService as ADS
from mantidqt.plotting.sample_shape_ads_observer import SampleShapePlotADSObserver
from workbench.plotting.globalfiguremanager import FigureAction, GlobalFigureManager


class SampleShapePlot:

    def __init__(self, ):
        self.ads_observer = None
        self.figure = None
        self.workspace_name = None
        self.plot_visible = None
        # self.GFM_plot_number = None

        self.GlobalFigureManager = GlobalFigureManager
        # Register with CurrentFigure that we want to know of any
        # changes to the list of plots
        self.GlobalFigureManager.add_observer(self)

    def notify(self, action, plot_number):
        """
        This is called by GlobalFigureManager when plots are created
        or destroyed, renamed or the active order is changed. This
        calls the presenter to update the plot list in the model and
        the view.

        IMPORTANT: Anything called here is not called from the main
        GUI thread. Changes in the view must be wrapped in a
        QAppThreadCall!

        :param action: A FigureAction corresponding to the event
        :param plot_number: The unique number in GlobalFigureManager
        """
        # if action == FigureAction.New:
        #     self.GFM_plot_number = plot_number
        if action == FigureAction.Closed:
            self.reset_class()
        if action == FigureAction.VisibilityChanged:
            self.plot_visible = self.is_visible(plot_number)

    def create_plot(self, workspace_name, figure=None):
        self.workspace_name = workspace_name
        sample_plotted = container_plotted = components_plotted = None
        workspace = ADS.retrieve(workspace_name)
        if figure:
            axes = figure.gca()
        else:
            self.plot_visible = True
            figure, axes = plt.subplots(subplot_kw={'projection': 'mantid3d'})

        if workspace.sample():
            sample_plotted = plot_sample_only(workspace, figure)
        if workspace.sample().hasEnvironment():
            container_plotted = plot_container(workspace, figure)
            number_of_components = workspace.sample().getEnvironment().nelements()
            if number_of_components > 1:
                components_plotted = plot_components(workspace, figure)

        add_title(sample_plotted, container_plotted, components_plotted, axes, workspace_name)
        set_axes_to_largest_mesh(axes, workspace)
        set_perspective(axes)
        set_axes_labels(axes)
        add_beam_arrow(axes, workspace)
        if workspace.sample().hasOrientedLattice():
            plot_lattice_vectors(axes, workspace)
        if sample_plotted or container_plotted or components_plotted:
            SampleShapePlot.ads_observer = SampleShapePlotADSObserver(self.on_replace_workspace,
                                                                      self.on_rename_workspace,
                                                                      self.on_clear, self.on_delete_workspace)
            if self.plot_visible:
                show_the_figure(figure)
            figure.canvas.draw()
            self.figure = figure
            return figure

    def reset_class(self):
        self.figure = None
        self.workspace_name = None
        self.ads_observer = None

    def is_visible(self, plot_number):
        """
        Determines if plot window is visible or hidden
        :return: True if plot visible (window open), false if hidden
        """
        figure_manager = self.GlobalFigureManager.figs.get(plot_number)
        if figure_manager is None:
            raise ValueError('Error in is_visible, could not find a plot with the number {}.'.format(plot_number))

        return figure_manager.window.isVisible()

    def on_replace_workspace(self, workspace_name):
        self.do_not_replace_plot_if_closed()

        if self.workspace_name == workspace_name:
            self.figure.gca().clear()
            self.create_plot(workspace_name=self.workspace_name, figure=self.figure)

    def do_not_replace_plot_if_closed(self):
        plot_is_open = False
        if self.figure:
            for manager in GlobalFigureManager.figs.values():
                if manager.canvas.figure == self.figure:
                    plot_is_open = True

        if not plot_is_open:
            self.reset_class()

    def on_rename_workspace(self, old_workspace_name, new_workspace_name):
        if self.workspace_name == old_workspace_name:
            self.workspace_name = new_workspace_name
            plot_axes = self.figure.gca()
            old_title = plot_axes.get_title()
            new_title = old_title.replace(old_workspace_name, new_workspace_name)
            plot_axes.set_title(new_title)

    def on_delete_workspace(self, workspace_name):
        if self.workspace_name == workspace_name:
            GlobalFigureManager.destroy_fig(self.figure)
            self.reset_class()

    def on_clear(self):
        GlobalFigureManager.destroy_fig(self.figure)
        self.reset_class()


def plot_sample_container_and_components(workspace_name):
    new_plot = SampleShapePlot()
    return new_plot.create_plot(workspace_name)


def is_shape_valid(shape):
    if is_mesh_not_empty(shape.getMesh()):
        return True


def is_mesh_not_empty(mesh):
    if len(mesh) > 3:
        return True


def get_valid_sample_shape_from_workspace(workspace):
    sample_shape = get_sample_shape_from_workspace(workspace)
    if is_shape_valid(sample_shape):
        return sample_shape


def get_sample_shape_from_workspace(workspace_with_sample):
    if workspace_with_sample.sample():
        return workspace_with_sample.sample().getShape()


def get_valid_container_shape_from_workspace(workspace):
    container_shape = get_container_shape_from_workspace(workspace)
    if is_shape_valid(container_shape):
        return container_shape


def get_container_shape_from_workspace(workspace_with_container):
    if workspace_with_container.sample():
        return workspace_with_container.sample().getEnvironment().getContainer().getShape()


def get_valid_component_shape_from_workspace(workspace, component_index):
    component_shape = get_component_shape_from_workspace(workspace, component_index)
    if is_shape_valid(component_shape):
        return component_shape


def get_component_shape_from_workspace(workspace_with_components, component_index):
    if workspace_with_components.sample():
        return workspace_with_components.sample().getEnvironment().getComponent(component_index)


def plot_sample_only(workspace, figure):
    axes = figure.gca()
    # get shape and mesh vertices
    shape = get_valid_sample_shape_from_workspace(workspace)
    if shape:
        mesh = shape.getMesh()
        if len(mesh) < 13:
            face_colors = ['purple', 'mediumorchid', 'royalblue', 'b', 'red', 'firebrick',
                           'green', 'darkgreen', 'grey', 'black', 'gold', 'orange']
            mesh_polygon = Poly3DCollection(mesh, facecolors=face_colors, edgecolors='black', alpha=1.0, linewidths=0.1)
        else:
            mesh_polygon = Poly3DCollection(mesh, facecolors='red', edgecolors='black', alpha=1.0, linewidths=0.1)
            mesh_polygon.set_facecolor((1, 0, 0, 0.5))
        axes.add_collection3d(mesh_polygon)
        return True


def plot_container(workspace, figure):
    axes = figure.gca()
    container_shape = get_valid_container_shape_from_workspace(workspace)
    container_mesh = container_shape.getMesh()
    mesh_polygon = Poly3DCollection(container_mesh, edgecolors='black', alpha=0.1, linewidths=0.05, zorder=0.5)
    mesh_polygon.set_facecolor((0, 1, 0, 0.5))
    axes.add_collection3d(mesh_polygon)
    return True


def plot_components(workspace, figure):
    axes = figure.gca()
    number_of_components = workspace.sample().getEnvironment().nelements()
    for component_index in range(1, number_of_components):
        component_shape = get_valid_component_shape_from_workspace(workspace, component_index)
        component_mesh = component_shape.getMesh()
        mesh_polygon_loop = Poly3DCollection(component_mesh, edgecolors='black', alpha=0.1, linewidths=0.05, zorder=0.5)
        mesh_polygon_loop.set_facecolor((0, 0, 1, 0.5))
        axes.add_collection3d(mesh_polygon_loop)
    return True


def add_title(sample_plotted, container_plotted, components_plotted, plot_axes, name_of_workspace):
    title = construct_title(sample_plotted, container_plotted, components_plotted, name_of_workspace)
    plot_axes.set_title(title)


def construct_title(sample_plotted, container_plotted, components_plotted, name_of_workspace):
    title_string = ""
    if sample_plotted:
        title_string += "Sample"
    if container_plotted:
        if title_string:
            if components_plotted:
                title_string += ", "
            else:
                title_string += " and "
        title_string += "Container"
    if components_plotted:
        if title_string:
            title_string += " and "
        title_string += "Components"
    title_string += f": {name_of_workspace}"
    return title_string


def show_the_figure(plot_figure):
    plot_figure.show()


def set_axes_labels(plot_axes):
    plot_axes.set_xlabel('X / m')
    plot_axes.set_ylabel('Y / m')
    plot_axes.set_zlabel('Z / m')


def set_perspective(plot_axes):
    plot_axes.view_init(elev=15, azim=-135)


def call_set_mesh_axes_equal(axes, mesh):
    # not able to directly mock set_mesh_axes_equal() as part of MantidAxes3D, which inherits from matplotlib code
    axes.set_mesh_axes_equal(mesh)


def set_axes_to_largest_mesh(axes, workspace):
    overall_limits = overall_limits_for_all_meshes(workspace)
    call_set_mesh_axes_equal(axes, np.array(overall_limits))


def overall_limits_for_all_meshes(workspace, include_components=True):
    overall_limits = None
    sample_shape = get_valid_sample_shape_from_workspace(workspace)
    if sample_shape:
        overall_limits = overall_limits_for_every_axis(sample_shape.getMesh())
    if workspace.sample():
        if include_components and workspace.sample().hasEnvironment():
            environment = workspace.sample().getEnvironment()
            number_of_components = environment.nelements()
            for component_index in range(number_of_components):
                if component_index == 0:  # Container
                    loop_component_mesh = get_valid_container_shape_from_workspace(workspace).getMesh()
                else:
                    loop_component_mesh = get_valid_component_shape_from_workspace(workspace, component_index).getMesh()
                current_mesh_limits = overall_limits_for_every_axis(loop_component_mesh)
                overall_limits = greater_limits(current_mesh_limits, overall_limits)
        return overall_limits


def overall_limits_for_every_axis(mesh):
    if is_mesh_not_empty(mesh):
        flattened_mesh = mesh.flatten()
        minimum_x = flattened_mesh[0::3].min()
        maximum_x = flattened_mesh[0::3].max()
        minimum_y = flattened_mesh[1::3].min()
        maximum_y = flattened_mesh[1::3].max()
        minimum_z = flattened_mesh[2::3].min()
        maximum_z = flattened_mesh[2::3].max()
        return [minimum_x, minimum_y, minimum_z, maximum_x, maximum_y, maximum_z]
    else:
        return None


def compare_and_replace_minimum(new_limit, old_limit):
    output_limit = new_limit
    if old_limit < new_limit:
        output_limit = old_limit
    return output_limit


def compare_and_replace_maximum(new_limit, old_limit):
    output_limit = new_limit
    if old_limit > new_limit:
        output_limit = old_limit
    return output_limit


def greater_limits(new_limits, old_limits):
    # Set limits to new limits, and replace with old limits that are wider
    if old_limits:
        min_x = compare_and_replace_minimum(new_limits[0], old_limits[0])
        min_y = compare_and_replace_minimum(new_limits[1], old_limits[1])
        min_z = compare_and_replace_minimum(new_limits[2], old_limits[2])
        max_x = compare_and_replace_maximum(new_limits[3], old_limits[3])
        max_y = compare_and_replace_maximum(new_limits[4], old_limits[4])
        max_z = compare_and_replace_maximum(new_limits[5], old_limits[5])
    else:
        [min_x, min_y, min_z, max_x, max_y, max_z] = new_limits
    return [min_x, min_y, min_z, max_x, max_y, max_z]


def calculate_beam_direction(source, sample):
    source_position = source.getPos()
    sample_position = sample.getPos()
    beam_vector = sample_position - source_position
    return beam_vector


def add_beam_arrow(plot_axes, workspace):
    # Add arrow along beam direction
    source = workspace.getInstrument().getSource()
    sample = workspace.getInstrument().getSample()
    if source and sample:
        beam_origin = plot_axes.get_xlim3d()[0], plot_axes.get_ylim3d()[0], plot_axes.get_zlim3d()[0]
        beam_direction = calculate_beam_direction(source, sample)
        add_arrow(plot_axes, beam_direction, origin=beam_origin)


def add_arrow(ax, vector, origin=None, factor=None, color='black', linestyle='-'):
    # Add arrows for Beam or Crystal lattice
    if origin is None:
        origin = (ax.get_xlim3d()[1], ax.get_ylim3d()[1], ax.get_zlim3d()[1])
    if factor is None:
        lims = ax.get_xlim3d()
        factor = (lims[1]-lims[0]) / 3.0
    vector_norm = vector / np.linalg.norm(vector)
    ax.quiver(
        origin[0], origin[1], origin[2],
        vector_norm[0]*factor, vector_norm[1]*factor, vector_norm[2]*factor,
        color=color,
        linestyle=linestyle
    )


def plot_lattice_vectors(plot_axes, workspace):
    """Add arrows for real and reciprocal lattice vectors"""
    real_lattice_vectors, reciprocal_lattice_vectors = calculate_lattice_vectors(workspace)
    colors = ['r', 'g', 'b']
    plot_real_lattice_vectors(plot_axes, real_lattice_vectors, colors)
    plot_reciprocal_lattice_vectors(plot_axes, reciprocal_lattice_vectors, colors)


def plot_reciprocal_lattice_vectors(plot_axes, reciprocal_lattice, colors):
    for i in range(3):  # plot reciprocal_lattice with '--' dashed linestyle
        add_arrow(plot_axes, reciprocal_lattice[:, i], color=colors[i], linestyle='--')


def plot_real_lattice_vectors(plot_axes, real_lattice, colors):
    for i in range(3):  # plot real_lattice with '-' solid linestyle
        add_arrow(plot_axes, real_lattice[:, i], color=colors[i])


def calculate_lattice_vectors(workspace):
    ub_matrix = np.array(workspace.sample().getOrientedLattice().getUB())
    hkl = np.array([[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]])
    q_sample = np.matmul(ub_matrix, hkl)
    goniometer = workspace.getRun().getGoniometer().getR()
    reciprocal_lattice_vectors = np.matmul(goniometer, q_sample)  # QLab
    real_lattice_vectors = (2.0*np.pi)*np.linalg.inv(np.transpose(reciprocal_lattice_vectors))

    return real_lattice_vectors, reciprocal_lattice_vectors
